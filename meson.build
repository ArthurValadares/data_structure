project('Data structure', 'cpp', version : '1.0.0', license : 'MIT', default_options : ['cpp_std=c++20'])

inc = include_directories('include')

subdir('include')
subdir('src')

data_structure = static_library(
    'data_structure',
    sources,
    include_directories: inc,
)

pkg_mod = import('pkgconfig')
pkg_mod.generate(
    libraries : data_structure,
    version : '1.0',
    name : 'libdata-structure',
    filebase : 'data-structure',
    description : 'Uma biblioteca contendo implementações relativas à matéria de estrutura de dados'
)

