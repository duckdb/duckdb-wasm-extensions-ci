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
