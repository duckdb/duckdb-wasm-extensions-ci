#!/bin/bash

# Usage: ./extension-upload-wasm.sh <architecture> <commithash or version_tag>

set -e

# Ensure we do nothing on failed globs
shopt -s nullglob

if [[ -z "${DUCKDB_EXTENSION_SIGNING_PK}" ]]; then
	# no private key provided, use the test private key (NOT SAFE)
	# this is made so private.pem at the end of the block will be in
	# a valid state, and the rest of the signing process can be tested
	# even without providing the key
	cp test/mbedtls/private.pem private.pem
else
	# actual private key provided
	echo "$DUCKDB_EXTENSION_SIGNING_PK" > private.pem
fi

FILES="build/to_be_deployed/$2/$1/*.duckdb_extension.wasm"
for f in $FILES
do
        ext=`basename $f .duckdb_extension.wasm`
        echo $ext
        truncate $ext -s -256 > $.append
        # the actual payload, 256 bytes, to be added later
        ./compute-extension-hash.sh $f.append > $f.hash
        # encrypt hash with extension signing private key to create signature
        openssl pkeyutl -sign -in $f.hash -inkey private.pem -pkeyopt digest:sha256 -out $f.sign
        # append signature to extension binary
        cat $f.sign >> $f.append
        # compress extension binary
        brotli < $f.append > "$f.brotli"
        # upload compressed extension binary to S3
	if [[ -z "${AWS_SECRET_ACCESS_KEY}" ]]; then
		#AWS_SECRET_ACCESS_KEY is empty -> dry run
		aws s3 cp $f.brotli s3://duckdb-extensions-nightly/$2/$1/$ext.duckdb_extension.wasm --acl public-read --content-encoding br --content-type="application/wasm" --dryrun
	else
		aws s3 cp $f.brotli s3://duckdb-extensions-nightly/$2/$1/$ext.duckdb_extension.wasm --acl public-read --content-encoding br --content-type="application/wasm"
	fi
done

# remove private key
rm private.pem
