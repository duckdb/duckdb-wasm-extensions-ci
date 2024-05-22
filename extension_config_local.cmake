#
# This config file holds all out-of-tree extension that are built with DuckDB's CI
#
# to build duckdb with this configuration run:
#   EXTENSION_CONFIGS=.github/config/out_of_tree_extensions.cmake make
#


duckdb_extension_load(json DONT_LINK)
duckdb_extension_load(icu DONT_LINK)
duckdb_extension_load(parquet DONT_LINK)
duckdb_extension_load(autocomplete DONT_LINK)
duckdb_extension_load(excel DONT_LINK)
duckdb_extension_load(fts DONT_LINK)
duckdb_extension_load(httpfs DONT_LINK)
duckdb_extension_load(inet DONT_LINK)
duckdb_extension_load(icu DONT_LINK)
duckdb_extension_load(json DONT_LINK)
duckdb_extension_load(parquet DONT_LINK)
duckdb_extension_load(sqlsmith DONT_LINK)
duckdb_extension_load(tpcds DONT_LINK)
duckdb_extension_load(tpch DONT_LINK)

################# SQLITE_SCANNER
duckdb_extension_load(sqlite_scanner
        DONT_LINK LOAD_TESTS
        GIT_URL https://github.com/duckdb/sqlite_scanner
        GIT_TAG 50b7870be099186f195bc72bac5e9e11247ee2f9
        )

################# SUBSTRAIT
duckdb_extension_load(substrait
            LOAD_TESTS DONT_LINK
            GIT_URL https://github.com/duckdb/substrait
            GIT_TAG 237931391ebc7e6aee7aa81052fa1411f6c4128e
           )

duckdb_extension_load(vss
       LOAD_TESTS DONT_LINK
       GIT_URL https://github.com/duckdb/duckdb_vss
       GIT_TAG 690bfc56c82b54f4580dabbc2769e2925db61499
)
    duckdb_extension_load(azure
            LOAD_TESTS
            GIT_URL https://github.com/duckdb/duckdb_azure
            GIT_TAG 49b63dc8cd166952a0a34dfd54e6cfe5b823e05e
            )

#
################# SPATIAL
#duckdb_extension_load(spatial
 #   DONT_LINK LOAD_TESTS
 #   GIT_URL https://github.com/carlopi/duckdb_spatial.git
 #   GIT_TAG main
 #   INCLUDE_DIR spatial/include
 #   TEST_DIR test/sql
 #   LINKED_LIBS "../../deps/local/lib/*.a"
 #   )
