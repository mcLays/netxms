#!/bin/sh

hash1=__HASH1__
hash2=__HASH2__
skip=__SKIP__
command=__COMMAND__

trap '
	echo Cleanup...
	[ "x"$temp != "x" ] && rm -rf $temp
	exit
' INT EXIT

md5=`which md5 2>/dev/null`
if [ $? != 0 ]; then
	md5=`which md5sum 2>/dev/null`
	if [ $? != 0 ]; then
		md5=`which openssl 2>/dev/null`
		if [ $? != 0 ]; then
			echo "Can't calculate MD5, exiting"
			exit
		else
			md5="$md5 md5"
		fi
	fi
fi

if [ "X"`head -n$skip $0 | tail -n +5 | $md5 | cut -b1-32 | tr A-Z a-z` != "X"$hash1 ]; then
	echo Script MD5 mismach
	exit
fi
let "skip=skip+1" >/dev/null
if [ "X"`tail -n +$skip $0 | $md5 | cut -b1-32 | tr A-Z a-z` != "X"$hash2 ]; then
	echo Payload MD5 mismach
	exit
fi

temp=`mktemp -d /tmp/nxinst.XXXXXX 2>/dev/null`
if [ $? != 0 ]; then
	echo "Can't create temp dir"
	exit 0
fi
tail -n +$skip $0 | gzip -dc 2>/dev/null | tar xf - -C $temp
if [ $? != 0 ]; then
	echo "Can't unpack"
	exit;
else
	cd $temp
	chmod +x ./$command
	if [ $? != 0 ]; then
		echo "Can't chmod $command"
		exit
	fi
	./$command
fi

exit
###################################
