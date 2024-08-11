from attr import frozen, field


@frozen(eq=True)
class StdDependency:
    """

    StdDependency Class
    =======================

    This class represents a standard dependency.

    Class Attributes:
        - displayname : str : The name of the dependency.

    Methods:
        - __str__() : str : Returns a string representation of the dependency.

    Examples:
        dependency = StdDependency()
        dependency.displayname = "iostream"
        str(dependency) => "#include <iostream>"

    """
    displayname: str = field(eq=True)

    def __str__(self):
        return f"#include <{self.displayname}>"
