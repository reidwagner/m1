from distutils.core import setup, Extension

module1 = Extension('m1',
                    sources = ['src/m1.c'])

setup (name = 'M1',
       version = '0.0',
       description = 'A machine learning library',
       ext_modules = [module1])
