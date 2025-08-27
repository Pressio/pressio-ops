
# Scope

**pressio-ops** is a **header-only C++** library providing a **unified, free-function interface** for common linear-algebra operations across multiple backends. 

## What it offers
- **Type traits & MPL:** Utilities for detection and metaprogramming that help adapt to different data structures.
- **Expressions:** Lightweight expression helpers like `span`, `subspan`, `diagonal`, and `column` for slicing and views.
- **Ops (kernels):** BLAS-like building blocks—`dot`, norms, elementwise ops, `product` (matrix–vector/matrix–matrix), `scale`, `update`, `fill`, `set_zero`, `clone`, `deep_copy`, `resize`, and more—exposed as free functions (e.g., `pressio::ops::product(...)`).

## Why use it
- **One API, many backends:** Write operations once and use them with different linear-algebra libraries without refactoring your code.
- **Interoperability:** Designed to make coupling components less painful.
- **Lightweight:** Header-only.

# Website

https://pressio.github.io/pressio-ops/

# Hello World 

https://pressio.github.io/pressio-ops/helloworld.html


## Questions?

Find us on Slack: https://pressioteam.slack.com and/or
open an issue on [github](https://github.com/Pressio/pressio-ops/issues/new).


## License and Citation

[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

The full license is available [here](https://github.com/Pressio/pressio-ops/blob/main/LICENSE).
