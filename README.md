# Mini Spin-X Library

## Overview
Mini Spin-X is a cut down version of a "core" library I have been developing over the years to support my various coding projects, licensed under MIT. It has bunch of useful stuff like math library, xml parsing, loading/saving image files, file system, loading 3D assets, etc. for developing small programs. I have compiled it on different platforms, but because my main development environment is MSVC in Windows I only very occassionally check e.g. Linux/GCC. The library doesn't use STL but provides some alternatives e.g. for containers and has only few dependencies to external libs included in [`sxp_extlibs/`](sxp_extlibs/) dir. Everything should be included and just compile as is without need to download other libs. MSVC project/solution files can be found in [`build/`](builds/)

## Files & Dirs
### [`sxp_src/core/`](sxp_src/core) - Low-level core components
|File/Dir|Description|
|---|---|
|[`class.h`](sxp_src/core/class.h)|Generic class introspection and object management.|
|[`config.h`](sxp_src/core/config.h)|The library configuration file.|
|[`containers.h`](sxp_src/core/containers.h)|Collection of containers (e.g. `array`, `list`, `deque`, `hash_map`, etc.)|
|[`core.h`](sxp_src/core/core.h)|The most fundamental omnipresent core stuff. Always included either directly or indirectly.|
|[`crypto.h`](sxp_src/core/crypto.h)|Cryptographic functions (md5, sha256).|
|[`cstr.h`](sxp_src/core/cstr.h)|Low-level c-string functions.|
|[`enum.inc`](sxp_src/core/enum.inc)|Used to define enums with reflection.|
|[`expression.h`](sxp_src/core/expression.h)|Math expression parsing.|
|[`inet.h`](sxp_src/core/inet.h)|Network stuff.|
|[`iterators.h`](sxp_src/core/iterators.h)|Free iterators (e.g. for intrusive singly-linked lists.|
|[`main.h`](sxp_src/core/main.h)|For defining platform agnostic main().|
|[`memory.h`](sxp_src/core/memory.h)|Memory management classes.|
|[`meta.h`](sxp_src/core/meta.h)|Meta-progremming stuff.|
|[`node_graph.h`](sxp_src/core/node_graph.h)|Classes for generic node graph.|
|[`preprocessor.h`](sxp_src/core/preprocessor.h)|Preprocessor file parsing.|
|[`sort.h`](sxp_src/core/sort.h)|Sorting functions.|
|[`str.h`](sxp_src/core/str.h)|String management classes.|
|[`streams.h`](sxp_src/core/streams.h)|Stream library (abstract writing/reading data).|
|[`utils.h`](sxp_src/core/utils.h)|Just a bucket of misc "utility" stuff.|
|[`xml.h`](sxp_src/core/xml.h)|XML parsing.|
|[`zip.h`](sxp_src/core/zip.h)|ZIP file streams.|

### [`sxp_src/core/fsys/`](sxp_src/core/fsys) - File system
|File/Dir|Description|
|---|---|
|[`cipher_fsys.h`](sxp_src/core/fsys/cipher_fsys.h)|Extremely poor-security streams.|
|[`fsys.h`](sxp_src/core/fsys/fsys.h)|File system classes.|
|[`zip_fsys.h`](sxp_src/core/fsys/zip_fsys.h)|ZIP file system implementation (read files straight from ZIP file).|

### [`sxp_src/core/math/`](sxp_src/core/math) - Math library
|File/Dir|Description|
|---|---|
|[`bit_math.h`](sxp_src/core/math/bit_math.h)|Bit twiddling hacks.|
|[`color.h`](sxp_src/core/math/color.h)|Color classes (RGB/XYZ/YIQ/HSV) and functions.|
|[`fast_math.h`](sxp_src/core/math/fast_math.h)|Fast-math hacks.|
|[`geo3.h`](sxp_src/core/math/geo3.h)|3D geometry processing (calculating convex hull, bounding box)|
|[`math.h`](sxp_src/core/math/math.h)|Templated linear algebra classes (vector, matrix, quaternion, complex).|
|[`math_adv.h`](sxp_src/core/math/math_adv.h)|"Advanced" math.|
|[`monte_carlo.h`](sxp_src/core/math/monte_carlo.h)|Some Monte-Carlo sampling functions.|
|[`numeric.h`](sxp_src/core/math/numeric.h)|Numeric type traits.|
|[`optics.h`](sxp_src/core/math/optics.h)|Optics functions (BRDF, reflections, etc.)|
|[`parametric.h`](sxp_src/core/math/parametric.h)|Parametric surfaces and lines (Bezier, Hermite, etc.)|
|[`simd_math.h`](sxp_src/core/math/simd_math.h)|SIMD-optimized linear algebra classes.|
|[`tform3.h`](sxp_src/core/math/tform3.h)|Higher level 3D transform related classes (camera, affine transforms).|
|[`prim2/prim2.h`](sxp_src/core/math/prim2/prim2.h)|2D primitives.|
|[`prim2/prim2_isect.h`](sxp_src/core/math/prim2/prim2_isect.h)|2D primitive intersection functions.|
|[`prim3/prim3.h`](sxp_src/core/math/prim3/prim3.h)|3D primitives.|
|[`prim3/prim3_angle.h`](sxp_src/core/math/prim3/prim3_angle.h)|3D primitive angle functions.|
|[`prim3/prim3_bvol.h`](sxp_src/core/math/prim3/prim3_bvol.h)|3D primitive bounding volume functions.|
|[`prim3/prim3_dist.h`](sxp_src/core/math/prim3/prim3_dist.h)|3D primitive distance functions.|
|[`prim3/prim3_isect.h`](sxp_src/core/math/prim3/prim3_isect.h)|3D primitive intersection functions.|

### [`sxp_src/core/mp/`](sxp_src/core/mp) - Multiprocessing library
|File/Dir|Description|
|---|---|
|[`mp.h`](sxp_src/core/mp/mp.h)|Abstracted low-level multiprocessing funcs (atomics, threads, etc.)|
|[`mp_fiber.h`](sxp_src/core/mp/mp_fiber.h)|Fiber lib for co-operative multitasking.|
|[`mp_job_queue.h`](sxp_src/core/mp/mp_job_queue.h)|Light weight job queue.|
|[`mp_memory.h`](sxp_src/core/mp/mp_memory.h)|Thread-safe memory classes.|
|[`mp_msg_queue.h`](sxp_src/core/mp/mp_msg_queue.h)|Thread-safe message queue for interthread communication.|

### [`sxp_src/core_engine/`](sxp_src/core_engine) - Higher "engine" level core components
|File/Dir|Description|
|---|---|
|[`mesh.h`](sxp_src/core_engine/mesh.h)|Classes for loading and managing 3D meshes.|
|[`texture.h`](sxp_src/core_engine/texture.h)|Classes for loading and managing textures.|
|[`track_set.h`](sxp_src/core_engine/track_set.h)|Classes for loading and managing animation tracks.|
|[`loaders/`](sxp_src/core_engine/loaders/)|Loaders for asset files (used by [`mesh.h`](sxp_src/core_engine/mesh.h), [`texture.h`](sxp_src/core_engine/texture.h) and [`track_set.h`](sxp_src/core_engine/track_set.h)).|

### [`sxp_src/platform/`](sxp_src/platform) - Platform specific implementations
|File/Dir|Description|
|---|---|
|[`linux/`](sxp_src/platform/linux)|Core component implementations for Linux/GCC (file system, SIMD, multithreading, network, etc.)|
|[`posix/`](sxp_src/platform/posix)|Core component implementations for Posix|
|[`win/`](sxp_src/platform/win)|Core component implementations for Windows|

## License
Mini Spin-X Library is licensed under MIT license. See [LICENSE](LICENSE) for details.
