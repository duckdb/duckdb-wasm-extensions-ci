################# SPATIAL
duckdb_extension_load(spatial
    DONT_LINK LOAD_TESTS
    GIT_URL https://github.com/duckdb/duckdb_spatial.git
    GIT_TAG 6826755ec32aea77777b136cc81683fa9be4df7b
    INCLUDE_DIR spatial/include
    TEST_DIR test/sql
   LINKED_LIBS "../../deps/local/lib/*.a"
    )

