#!/bin/sh
make 
rm -f decoded.txt

start=`date +%s%3N`
cat encrypter.cpp | ./encrypter -p nagado | ./encrypter -p nagado >> decoded.txt
end=`date +%s%3N`
runtime=$((end-start))

if diff decoded.txt encrypter.cpp >/dev/null; then
    echo "It took $runtime ms"
else
    echo "The program doesn't work properly"
fi

rm -f decoded.txt
