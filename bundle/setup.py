from setuptools import setup, find_packages

setup(
    name='bundle',
    version='0.1.0',
    packages=find_packages(),
    include_package_data=True,
    install_requires=[
        'Click',
    ],
    entry_points={
        'console_scripts': [
            'bundle = src.script.bundle:main',
        ],
    },
)
