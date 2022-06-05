import os
from distutils.core import Extension, setup

setup(
    name="perlin",
    version="-0.0.0.1",
    description="This module can produce a lot of bugs, ideally perlin noise 2d/3d",
    author="Andrii R.",
    author_email="roykoand@gmail.com",
    ext_modules=[Extension("perlin", [os.path.join("src", "perlin.c")])],
)
