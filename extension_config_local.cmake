#
# This config file holds all out-of-tree extension that are built with DuckDB's CI
#
# to build duckdb with this configuration run:
#   EXTENSION_CONFIGS=.github/config/out_of_tree_extensions.cmake make
#

############### SPATIAL

    duckdb_extension_load(spatial
            DONT_LINK LOAD_TESTS
            GIT_URL https://github.com/carlopi/duckdb_spatial.git
            GIT_TAG main
            INCLUDE_DIR spatial/include
            TEST_DIR test/sql
            LINKED_LIBS "../../deps/local/lib/*.a"
           )

################# SQLITE_SCANNER
duckdb_extension_load(sqlite_scanner
        DONT_LINK LOAD_TESTS
        GIT_URL https://github.com/duckdb/sqlite_scanner
        GIT_TAG 091197efb34579c7195afa43dfb5925023c915c0
        )

################# SUBSTRAIT
duckdb_extension_load(substrait
            LOAD_TESTS DONT_LINK
            GIT_URL https://github.com/duckdb/substrait
            GIT_TAG 1116fb580edd3e26e675436dbdbdf4a0aa5e456e
           )

duckdb_extension_load(vss
       LOAD_TESTS DONT_LINK
       GIT_URL https://github.com/duckdb/duckdb_vss
       GIT_TAG 8145f41d97178e82bed3376215eb8d02bcf1eec5
)
    duckdb_extension_load(azure
            LOAD_TESTS
            GIT_URL https://github.com/duckdb/duckdb_azure
            GIT_TAG 09623777a366572bfb8fa53e47acdf72133a360e
            )
