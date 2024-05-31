################# SPATIAL
duckdb_extension_load(spatial
    DONT_LINK LOAD_TESTS
    GIT_URL https://github.com/duckdb/duckdb_spatial.git
    GIT_TAG 9cf8b2915c28b6139e8573cd64869941f598541c
    INCLUDE_DIR spatial/include
    TEST_DIR test/sql
    LINKED_LIBS "../../deps/local/lib/*.a"
    )

