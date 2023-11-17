
Please find included the submission of the adbcsnowflake package, a 'Snowflake'
driver written in Go with R bindings via the adbcdrivermanager package. As
discussed on the R-pkg-devel mailing list [1], this package is a thin wrapper
around a library written in Go, with which a static library is built.
Because the Go dependencies are large, the dependency sources are downloaded
at runtime, are checksum verified, and copied to the source directory for use
during build to comply with CRAN policy. Simon has kindly installed Go on
the MacOS runner...to build on Windows it would be necessary to install Go
and set GO_BIN if installed in a non-default location.

Following the first submission, this package also correctly sets GOPATH
and GOCACHE to ensure that files are not written to the user's home directory.
Additionally, fallback checksum detection using the openssl or digest
packages is included in the event that `shasum` is not available.

[1] https://stat.ethz.ch/pipermail/r-package-devel/2023q3/009329.html

## R CMD check results

0 errors | 0 warnings | 1 note

* This is a new release.
