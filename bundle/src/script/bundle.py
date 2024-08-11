import os
import pathlib
from pathlib import Path
from typing import Optional

import click

from ..config import CONFIG_FILE_NAME, Config
from ..dependency.graph import DependencyGraph, STD_PATTERN, PROJECT_PATTERN
from ..dependency.std import StdDependency


@click.group()
def main():
    """
    Main method for the program.

    :return: None
    """
    pass


@main.command(help="Initializes a directory with a bundle.config.json file")
@click.argument("project_root", type=click.Path(path_type=pathlib.Path, file_okay=False, dir_okay=True, exists=True),
                default=Path(os.getcwd()))
@click.option("--force", "-f", is_flag=True)
def init(project_root: Path, force: bool):
    """
    :param project_root: The root directory where the initialization will be performed.
    :param force: Flag indicating whether to force the initialization process even if a config file already exists in the current directory.
    :return: None

    Initializes a directory by creating a bundle.config.json file. If a config file already exists in the current directory and the force flag is not set, the initialization process is skipped.

    Parameters:
    - project_root: The root directory where the initialization will be performed. This should be a valid directory path.
    - force: A boolean flag indicating whether to force the initialization process even if a config file already exists in the current directory. If set to True, the existing config file will be overwritten. If set to False (default), the initialization process will be skipped if a config file already exists.

    Example Usage:
    ```
    init("/path/to/project", True)
    ```
    """
    project_root = Path(project_root).resolve()
    cwd = Path(os.getcwd())
    if not (cwd / CONFIG_FILE_NAME).exists() or force:
        config = Config(project_root)
        file_name = cwd / CONFIG_FILE_NAME
        config.write_on(file_name)
    else:
        click.echo(f"The config file {CONFIG_FILE_NAME} already exists on {cwd}")


@main.command(help="Bundles the file provided as an argument using the bundle.config.json contained in the directory "
                   "or some parent directory to a output file")
@click.argument("FILE", type=click.Path(file_okay=True, dir_okay=False, exists=True, path_type=pathlib.Path),
                default=None, required=True)
@click.argument("OUTPUT", type=click.Path(file_okay=True, dir_okay=True, exists=True, path_type=pathlib.Path),
                default=None, required=True)
@click.option("--force", type=click.BOOL, is_flag=True)
def bundle(file: Optional[Path], output: Optional[Path], force: bool):
    """
    :param file: Path to the file to be bundled.
    :param output: Path to the output file or directory.
    :param force: Flag indicating whether to overwrite the output file if it already exists.
    :return: None

    Bundles the file provided as an argument using the `bundle.config.json` contained in the directory or some parent directory to an output file.

    Example usage:
        bundle("input.txt", "output.txt", True)
    """
    config = Config.from_config_in_some_parent_directory(file.parent)
    graph = DependencyGraph.from_file(file, config)

    path = output if output.is_file() else output / file.name
    if (path.exists() and path.is_file()) and not force:
        raise Exception(f'The target file already exists. If it is not a error, use --force')

    sorted_nodes = graph.topologic_sort()
    sorted_nodes.reverse()

    with open(path, 'w') as output_file:
        for node in sorted_nodes:
            if isinstance(node, StdDependency):
                output_file.write(f'{node}\n')
            else:
                with open(node.path) as header_file:
                    for line in header_file:
                        project_match = PROJECT_PATTERN.match(line)
                        std_match = STD_PATTERN.match(line)
                        if project_match is None and std_match is None:
                            output_file.write(line)

                output_file.write("\n")

                if not node.is_header_only():
                    with open(node.implementation) as implementation_file:
                        for line in implementation_file:
                            project_match = PROJECT_PATTERN.match(line)
                            std_match = STD_PATTERN.match(line)
                            if project_match is None and std_match is None:
                                output_file.write(line)

                    output_file.write("\n")


@main.command(help="Show the dependency graph of a given file")
@click.argument("FILE", type=click.Path(file_okay=True, dir_okay=False, exists=True, path_type=pathlib.Path),
                default=None, required=True)
def show(file: Path):
    """
    Show the dependency graph of a given file.

    :param file: A Path object representing the file to generate the graph for.
    :return: None.
    """
    config = Config.from_config_in_some_parent_directory(file.parent)
    graph = DependencyGraph.from_file(file, config)
    graph.draw()


if __name__ == "__main__":
    main()
