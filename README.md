# game-engine

CS 438 game project

## Table of Contents

- [Dependencies](#dependencies)
- [Building the Project](#building-the-project)
- [Testing the Project](#testing-the-project)
- [Running the Project](#running-the-project)
- [Utilizing Pre-commit](#utilizing-pre-commit)
- [LICENSE](#license)

## Dependencies
* C++20
* Python3

## Building the Project

To build the project, follow these steps:

1. Open a terminal and navigate to the project root directory.
2. Run the following commands:

```
   bash
   mkdir build
   cd build
   cmake ..
   make
```
## Testing the Project

To run tests, use the following command:
```
ctest
```

## Running the Project

To run the project, execute the generated executable from the build directory:
```
./main
```

## Utilizing Pre-commit
This project uses pre-commit hooks to ensure code quality before commits. Follow these steps to install and run pre-commit:

Install pre-commit using pip:
```
pip install pre-commit
```

Set up pre-commit hooks:
```
pre-commit install
```

Run pre-commit on all files:
```
pre-commit run --all-files
```

## License

This project is licensed under the zlib License - see the [LICENSE](LICENSE) file for details.
