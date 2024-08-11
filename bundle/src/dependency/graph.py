import re
from collections import deque
from pathlib import Path
from queue import Queue
from typing import Union, Dict, Set, Tuple, Optional, List

import networkx as nx
from attr import define, field
from matplotlib import pyplot as plt
from rich.console import Console
from rich.console import Group
from rich.live import Live
from rich.panel import Panel
from rich.progress import Progress, TextColumn, BarColumn

from ..config import Config
from .project import ProjectDependency
from .std import StdDependency

# Compiles regular expressions against the standard library and project files
STD_PATTERN = re.compile(r'#include\s+<([^<>"]+)>')
PROJECT_PATTERN = re.compile(r'#include\s+"(.+?)"')

Dependency = Union[StdDependency, ProjectDependency]


@define
class DependencyGraph:
    """
    Represents a dependency graph where nodes are projects and edges represent dependencies between projects.

    Attributes:
        __adjacence_list (Dict[ProjectDependency, Set[Dependency]]): The adjacency list representation of the graph, where
        each project is a key and its dependencies are its values.

    Properties:
        vertices (Set[Dependency]): Returns a set of all dependencies in the graph, including projects and standard
        dependencies.

        edges (Set[Tuple[ProjectDependency, Dependency]]): Returns a set of tuples, where each tuple represents an edge
        between a project and its dependency.

        root (Optional[ProjectDependency]): Returns the root project in the dependency graph, i.e., the project that
        doesn't have any dependencies.

    Methods:
        __getitem__(self, item: ProjectDependency) -> Set[Dependency]: Returns the set of dependencies of a given project.

        __setitem__(self, key: ProjectDependency, value: Set[Dependency]): Sets the dependencies of a project.

        parents_of(self, child: Dependency) -> List[ProjectDependency]: Returns a list of projects that are parents of a
        given dependency in the graph.

        from_file(relative_path: Path, config: Config) -> 'DependencyGraph': Reads a file and creates a dependency
        graph based on the file's content and a configuration object.

        topologic_sort(self) -> List[Dependency]: Returns a topological sorting of the projects in the graph.

        draw(self): Displays a graphical representation of the dependency graph.
    """
    __adjacence_list: Dict[ProjectDependency, Set[Dependency]] = field(default=dict())

    @property
    def vertices(self) -> Set[Dependency]:
        """Get the set of all vertices in the dependency graph.

        :return: A set of Dependency objects representing all the vertices in the graph.
        :rtype: set[Dependency]
        """
        keys = set(self.__adjacence_list.keys())
        others = set().union(*self.__adjacence_list.values())
        return keys.union(others)

    @property
    def edges(self) -> Set[Tuple[ProjectDependency, Dependency]]:
        """
        Returns a set containing all the edges in the graph.

        :return: A set of tuples representing the edges in the graph. Each tuple consists of a `ProjectDependency` object as the first element and a `Dependency` object as the second element.
        :rtype: set of tuple[ProjectDependency, Dependency]
        """
        return {(key, item) for key, value in self.__adjacence_list.items() for item in value}

    @property
    def root(self) -> Optional[ProjectDependency]:
        """
        Root method

        :return: The root project dependency, which is the top-level node in the project dependency graph
        :rtype: Optional[ProjectDependency]
        """
        children: Set[Dependency] = set().union(*self.__adjacence_list.values())
        for node in self.__adjacence_list.keys():
            if node not in children:
                return node
        return None

    def __getitem__(self, item: ProjectDependency) -> Set[Dependency]:
        """
        Retrieve the dependencies associated with a given project dependency item.

        :param item: The project dependency item for which to retrieve the dependencies.
        :type item: ProjectDependency
        :return: The set of dependencies associated with the given project dependency item.
        :rtype: Set[Dependency]
        """
        return self.__adjacence_list[item]

    def __setitem__(self, key: ProjectDependency, value: Set[Dependency]):
        """
        :param key: The key used to access the value in the dictionary.
        :type key: ProjectDependency
        :param value: The value to be assigned to the key in the dictionary.
        :type value: Set[Dependency]
        :return: None

        Sets the value of the specified key to the given value in the dictionary.
        """
        self.__adjacence_list[key] = value

    def parents_of(self, child: Dependency) -> List[ProjectDependency]:
        """
        :param child: The Dependency object representing the child for which the parents need to be found.
        :return: A list of ProjectDependency objects representing the parents of the given child.
        """
        nodes: Queue[ProjectDependency] = Queue()
        nodes.put(child)

        parents: List[ProjectDependency] = list()

        while not nodes.empty():
            node = nodes.get()
            for parent, children in self.__adjacence_list.items():
                if node in children:
                    parents.append(parent)
                    nodes.put(parent)

        return parents

    @staticmethod
    def from_file(relative_path: Path, config: Config) -> 'DependencyGraph':
        """
        :param relative_path: The relative path to the file that will be processed.
        :param config: The configuration object used to retrieve project information.
        :return: The constructed DependencyGraph object.

        This method takes a relative path to a file and a config object as parameters. It processes the file and constructs a DependencyGraph based on its contents. The method uses a queue to keep track of files that need to be processed.

        The method starts by creating a console object and printing a message indicating the start of the processing. It then creates an empty DependencyGraph object.

        Next, it creates a root ProjectDependency object based on the provided relative path and adds it to the queue of files to be processed. It also creates a Progress object for tracking the progress of file processing.

        The method then enters a loop that continues as long as there are files in the queue. Inside the loop, it retrieves a file from the queue and checks if it exists. If the file does not exist, it raises a ValueError with an appropriate error message.

        The method appends a log message indicating that the file is being processed and updates the display. It then adds the current file as a key in the DependencyGraph with an empty set as its value.

        Next, it opens the file and reads its contents. It uses regular expressions to find dependencies based on specific patterns. If it finds standard library dependencies, it creates StdDependency objects and adds them to the set of dependencies of the current file in the DependencyGraph.

        If it doesn't find any standard library dependencies, it appends a log message indicating that the file does not contain direct dependencies of the standard library.

        The method then uses regular expressions to find project dependencies. If it finds any, it resolves their paths based on the current file's path and the project root path from the config object. It creates ProjectDependency objects for these dependencies and adds them to the set of dependencies of the current file in the DependencyGraph. It also adds these project dependencies to the queue for processing.

        The method updates the progress by incrementing the total count of files to be processed.

        If it doesn't find any project dependencies, it appends a log message indicating that the file does not contain project dependencies.

        The method then advances the progress and appends a log message indicating that the current file has been processed.

        After processing all files, the method appends a log message indicating the completion of file processing.

        Finally, it returns the constructed DependencyGraph object.
        """
        console = Console()
        console.print(f'Starting to process the file: {relative_path}')

        graph = DependencyGraph()

        root = ProjectDependency(path=relative_path)
        files_to_process: Queue[ProjectDependency] = Queue()
        files_to_process.put(root)

        progress = Progress(
            TextColumn("[progress.description]{task.description}"),
            BarColumn(),
            TextColumn("[progress.percentage]{task.percentage:>3.0f}%"),
            expand=True
        )

        log_panel = Panel("Logs will appear here", title="Logs")
        log_messages = []

        sources_names_and_path: Dict[str, Path] = {source.stem: source for source in config.all_source_files()}

        with Live(console=console, refresh_per_second=10) as live:
            task_id = progress.add_task("Processing files", total=1)
            live.update(Group(log_panel, progress))

            while not files_to_process.empty():
                node = files_to_process.get()
                if not node.path.exists():
                    parents_path = [parent.path for parent in graph.parents_of(node)]
                    raise ValueError(
                        f'The target file {node.path} does not exist. Check on the following files {parents_path}')

                log_messages.append(f'Processing file {node.path}')
                log_panel = Panel("\n".join(log_messages), title="Logs")
                live.update(Group(log_panel, progress))

                graph[node] = set()

                with open(node.path, 'r+') as file:
                    content = file.read()

                    std_matches = STD_PATTERN.findall(content)
                    if std_matches:
                        for name in std_matches:
                            std_dependency = StdDependency(name)
                            graph[node].add(std_dependency)
                    else:
                        log_messages.append(f'{node.path} does not contain direct dependencies of the standard '
                                            f'library. Great!')
                        log_panel = Panel("\n".join(log_messages), title="Logs")
                        live.update(Group(log_panel, progress))

                    project_matches = PROJECT_PATTERN.findall(content)
                    if project_matches:
                        for project_file_path in project_matches:
                            relative_path = (node.path.parent / project_file_path).resolve()
                            project_root_path = (config.project_root / project_file_path).resolve()
                            path = relative_path if relative_path.exists() else project_root_path

                            log_messages.append(f'Reference to {relative_path} found on {node.path}')
                            log_panel = Panel("\n".join(log_messages), title="Logs")
                            live.update(Group(log_panel, progress))

                            project_dependency = ProjectDependency(path, sources_names_and_path.get(path.stem))
                            graph[node].add(project_dependency)

                            files_to_process.put(project_dependency)

                            progress.update(task_id, total=progress.tasks[task_id].total + 1)

                    else:
                        log_messages.append(f'{node.path} does not contain project dependencies.')
                        log_panel = Panel("\n".join(log_messages), title="Logs")
                        live.update(Group(log_panel, progress))

                progress.advance(task_id)

                log_messages.append(f'{node.path} processed!')
                log_panel = Panel("\n".join(log_messages), title="Logs")
                live.update(Group(log_panel, progress))

            log_messages.append('Finished processing all files.')
            log_panel = Panel("\n".join(log_messages), title="Logs")
            live.update(Group(log_panel, progress))

        return graph

    def topologic_sort(self) -> List[Dependency]:
        """
        Performs a topological sort on the graph.

        :return: A list of Dependency objects sorted in topological order.
        :rtype: List[Dependency]
        """
        sorted_elements = list()
        visited: Set[Dependency] = set()

        in_degree = {u: 0 for u in self.vertices}
        for _, value in self.__adjacence_list.items():
            for v in value:
                in_degree[v] += 1

        nodes_without_incoming_edges = deque([u for u in self.vertices if in_degree[u] == 0])

        while nodes_without_incoming_edges:
            n = nodes_without_incoming_edges.popleft()
            if n not in visited:
                visited.add(n)
                sorted_elements.append(n)
                children = self.__adjacence_list.get(n)
                for m in children or []:
                    in_degree[m] -= 1
                    if in_degree[m] == 0:
                        nodes_without_incoming_edges.append(m)

        if any(in_degree[u] > 0 for u in in_degree):
            raise RuntimeError('O grafo tem, pelo menos, um ciclo')

        return sorted_elements

    def draw(self):
        """
        Draw method creates a directed graph using adjacency list and displays it using NetworkX library's draw function.

        :return: None
        """
        graph = nx.DiGraph()

        for node, children in self.__adjacence_list.items():
            graph.add_node(node.displayname)
            for child in children:
                graph.add_edge(node.displayname, child.displayname)

        pos = nx.spring_layout(graph)  # Adjust k and iterations for better spacing
        nx.draw(graph, pos, with_labels=True, node_size=3000, node_color="lightblue", font_size=10, font_weight="bold")
        plt.show()
