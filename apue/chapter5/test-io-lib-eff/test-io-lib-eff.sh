#!/bin/sh

TEST_DIR=$HOME/tmp/test-io-lib-eff
rm $TEST_DIR/*

test_io_lib_eff() {
    TEMP_FILE=`mktemp --tmpdir=$TEST_DIR "test-io-lib-eff-$(date +%T)-XXXXXX"`
    echo "TEMP_FILE=$TEMP_FILE"
    #touch $TEMP_FILE
    dd if=/dev/zero of=$TEMP_FILE bs=10M count=100

    time $1 <$TEMP_FILE >$TEMP_FILE.copy;
    unlink $TEMP_FILE
    unlink $TEMP_FILE.copy
}


for prog in $@;
do
    echo "\n==========================="
    echo "testing $prog"
    test_io_lib_eff $PWD/$prog;
done

