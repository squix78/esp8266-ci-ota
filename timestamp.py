from time import time, gmtime, strftime

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
env.Append(CPPDEFINES=['BUILD_TIMESTAMP="%s"' % strftime("%Y%m%d", gmtime())])
