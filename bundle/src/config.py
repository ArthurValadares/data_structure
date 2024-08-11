import json
from pathlib import Path
from typing import List, Optional

from attr import define

CONFIG_FILE_NAME = "bundle.config.json"


@define
class Config:
    """
    Represents a configuration object.

    Attributes:
        project_root (Path): The root directory of the project.
        sources (List[Path]): The list of source directories.

    Methods:
        write_on(self, path: Path) -> None:
            Writes the configuration object to a file.

        from_file(path: Path) -> Config:
            Loads the configuration object from a file.

        from_config_in_some_parent_directory(path: Path) -> Optional[Config]:
            Loads the configuration object from a file in the parent directory or any ancestor directory.

        to_dict(self) -> dict:
            Converts the configuration object to a dictionary.

        all_source_files(self) -> List[Path]:
            Returns a list of all source files in the source directories.
    """
    project_root: Path
    sources: List[Path] = list()

    def write_on(self, path: Path):
        """
        Write the configuration object to a file.

        :param path: The path to the file to write the configuration to.
        :type path: Path

        :raises ValueError: If the target directory does not exist
        :raises ValueError: If the file is not named `CONFIG_FILE_NAME`

        :return: None
        """
        if not path.parent.exists():
            raise ValueError(f'The target directory does not exist: {path.parent}')

        if path.name != CONFIG_FILE_NAME:
            raise ValueError(f'The file should be named {CONFIG_FILE_NAME}')

        with open(path, 'w') as file:
            json.dump(self.to_dict(), file, indent=2)

    @staticmethod
    def from_file(path: Path) -> 'Config':
        """
        Reads a configuration object from a file.

        :param path: The path to the file.
        :return: A `Config` object.
        :raises ValueError: If the target file does not exist or if it is not named `CONFIG_FILE_NAME`.
        """
        if not path.exists():
            raise ValueError(f'The target file does not exist: {path}')

        if path.name != CONFIG_FILE_NAME:
            raise ValueError(f'The target file should be named {CONFIG_FILE_NAME}')

        with open(path, 'r') as file:
            data = json.load(file)
            return Config(
                project_root=Path(data['project_root']),
                sources=[Path(source) for source in data.get('sources', [])]
            )

    @staticmethod
    def from_config_in_some_parent_directory(path: Path) -> Optional['Config']:
        """
        :param path: A Path object representing the directory from which to search for the configuration file.
        :return: An optional instance of 'Config' if a configuration file is found, otherwise None.
        """
        for parent in [path] + list(path.parents):
            potential_file = parent / CONFIG_FILE_NAME
            if potential_file.exists() and potential_file.is_file():
                return Config.from_file(potential_file)

        return None

    def to_dict(self) -> dict:
        """
        Convert the object into a dictionary.

        :return: A dictionary representing the object.
        :rtype: dict
        """
        return {
            'project_root': str(self.project_root),
            'sources': [str(source) for source in self.sources]
        }

    def all_source_files(self) -> List[Path]:
        """
        Get all source files from the given sources.

        :return: A list of paths to the source files.
        :rtype: List[Path]
        """
        return [file for source in self.sources for file in source.rglob("*.cpp") if file.is_file()]
