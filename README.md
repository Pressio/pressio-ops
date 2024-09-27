
# Pressio/pressio-ops

`Pressio/pressio-ops` separates the operations[^1] from the rest of the [`Pressio/pressio`](https://github.com/Pressio/pressio) repository.

## This repository should NOT be used (yet)

The goal is for users to be able to clone and use this repository on its own, without requiring the rest of `Pressio/pressio`.

`Pressio/pressio`, in turn, would be generic because the remaining components (`solvers`, `ode`, and `rom`) would be written in terms of operations.

> [!CAUTION]
> Until we have confirmed that this is the approach we want to take, this repository should NOT be used, and users should instead continue using the full `Pressio/pressio` code.

## License and Citation

[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

The full license is available [here](https://github.com/Pressio/pressio-ops/blob/main/LICENSE).

[^1]: The operations are `ops`, `expressions`, `type_traits`, and `mpl`

<!-- ## Questions?
Find us on Slack: https://pressioteam.slack.com and/or
open an issue on [github](https://github.com/Pressio/pressio).

## License and Citation

[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

The full license is available [here](https://pressio.github.io/various/license/).

At some point we plan to publish this, for now we have an arXiv preprint at: https://arxiv.org/abs/2003.07798.

 -->

<!-- [![Codecove](https://codecov.io/gh/Pressio/pressio/branch/master/graphs/badge.svg?precision=2)](https://codecov.io/gh/Pressio/pressio/branch/master) -->
