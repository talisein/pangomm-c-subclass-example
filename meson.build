

project('pango-example', ['c', 'cpp'],
        license : 'GPLv3+',
        version : '0.0.1',
        default_options : ['c_std=c17',
                           'cpp_std=c++20',
                           'buildtype=release'])

pangomm_dep  = dependency('pangomm-2.48')

src = [
  'main.cpp',
  'pango_font_map_osg.cpp',
  'pango_font_osg.cpp',
  'pango_renderer_osg.cpp',
]

exe = executable('pango_example', src,
                 dependencies: pangomm_dep)
