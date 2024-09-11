cpmaddpackage(
    NAME mold
    VERSION 2.32.0
    URL https://github.com/rui314/mold/releases/download/v2.32.0/mold-2.32.0-x86_64-linux.tar.gz
    URL_HASH SHA256=17e7ed0fd4877fbf24d13a830bd325ce3ebd05434800af9296b6c576fcc0414e
    DOWNLOAD_ONLY True
)

set(MOLD
    ${mold_bin_SOURCE_DIR}/bin/mold
    CACHE FILEPATH "mold linker" FORCE
)
