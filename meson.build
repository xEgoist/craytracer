project('craytracer', 'c',
  version : '0.1',
  default_options : ['warning_level=3','c_std=c2x','buildtype=release','optimization=s','strip=true']
  )
library_path = []
project_sources = []
project_header_files = []
inc = [include_directories('include')]
subdir('include')
subdir('src')
#getting the current system compiler
cc = meson.get_compiler('c')
# add the math library so linux can recognize it
m_dep = cc.find_library('m',required: false)

executable('craytracer',
          main_source,
          include_directories: inc,
          install : true,
          dependencies: m_dep)
