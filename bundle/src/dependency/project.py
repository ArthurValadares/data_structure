from pathlib import Path
from typing import Optional

from attr import frozen, field


@frozen(eq=True)
class ProjectDependency:
    """
    ProjectDependency Class

    A class representing a project dependency.

    Attributes:
        path (Path): The path to the library header file.
        implementation (Optional[Path]): The path to the library implementation file (optional).

    Methods:
        is_header_only: Returns True if the dependency is a header-only library.
        displayname: Returns the display name of the dependency.
        __str__: Returns a string representation of the dependency.

    """
    path: Path = field(eq=True)
    implementation: Optional[Path] = field(default=None, eq=False)

    def is_header_only(self):
        """
        Check if the method is a header-only method.

        :return: True if the method does not have an implementation, False otherwise.
        """
        return self.implementation is None

    @property
    def displayname(self) -> str:
        """
        Return the display name of the current path.

        :return: The display name of the current path.
        :rtype: str
        """
        return self.path.name

    def __str__(self):
        return f'#include "{self.path}"'
