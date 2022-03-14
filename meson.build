project('craytracer', 'c',
  version : '0.1',
  default_options : ['warning_level=3']
  )


library_path = []
project_sources = []
project_header_files = []
inc = [include_directories('include')]
subdir('include')
subdir('src')


executable('craytracer',
          main_source,
          include_directories: inc,
          install : true)
