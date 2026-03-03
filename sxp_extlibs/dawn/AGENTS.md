# AGENTS.md

## Vendored snapshot scope
- This Dawn tree is a client-facing vendored source snapshot, not an upstream development checkout.
- Retain only files needed to compile Dawn/Tint for the required target platforms: Windows, macOS, and Linux.
- Supported graphics backends in this snapshot are `d3d12`, `metal`, `vulkan`, and `null`.
- Do not retain legacy backend support such as `d3d11`, `opengl`, or `opengles`.

## Pruning rules
- Remove upstream development-only content from this snapshot: tests, benchmarks, fuzzers, samples, tools, generators, language-server code, replay/wire helpers, and other non-client utility layers unless the retained runtime code directly depends on them.
- Remove build-system and project-setup files from this snapshot: `CMake`, `GN`, `Bazel`, `BUILD.*`, `.gn`, `.gni`, `.cfg`, and similar metadata.
- If generated files are needed for compilation, generate them first and keep only the generated compile outputs. Remove the generator inputs/tools/config files afterward when they are not needed by the final C/C++ build.
- Delete upstream generator definition inputs such as Tint `*.def` files after their generated C++ outputs are present and retained.
- Keep license/readme files that should ship with the vendored snapshot.
- Keep `sxp_extlibs/build/dawn.sxproj` aligned with the pruned tree: do not add or keep `FileConfig` entries for files or filename patterns that no longer exist in this snapshot.
- When pruning removes files that were previously mentioned in `dawn.sxproj`, remove the stale `FileConfig` entries in the same task before regenerating the Visual Studio projects.
- Delete source/header files that exist only for non-target platforms instead of merely excluding them from the project. For this snapshot, remove Android/Fuchsia/iOS/OHOS/QNX/GGP/DirectFB/VI-only files, while retaining Windows/macOS/Linux files and Linux window-system support needed for Vulkan (`xlib`, `xcb`, `wayland`).
- Prefer deleting single-file `Exclude="1"` entries from the snapshot instead of keeping excluded one-off files in the tree. If a file is intentionally excluded and has no remaining target-platform purpose, delete the file and remove the `FileConfig` entry in the same task.
- Apply the same rule to whole directories: if an entire feature directory is excluded from `dawn.sxproj` and is not needed by the retained target-platform/client runtime, delete the directory and remove the matching `FileConfig` entry instead of leaving dead excluded trees behind.

## File-type rules
- Keep only compile-relevant source/header files and required generated include fragments for the retained platforms and backends.
- Keep platform-required compile inputs even when they use non-`.c`/`.cc`/`.cpp`/`.h`/`.hpp` extensions, such as Objective-C++ `.mm`, when they are required for macOS/Metal builds.
- Do not keep helper headers or sources whose only purpose is upstream testing, validation tooling of generated shaders, or standalone developer workflows.
