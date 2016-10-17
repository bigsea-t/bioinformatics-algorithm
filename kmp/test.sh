input_files=(`ls *.in`)
n_files=${#input_files[@]}

n_failed=0

g++ -std=c++11 kmp.cpp -o kmp

for i in `seq 1 $n_files`; do
	./kmp < $i.in  | diff $i.out -

	if [ $? -eq 0 ] ; then
	   echo "test$i passed"
	elif [ $? -eq 1 ] ; then
	    echo "test$i failed"
	    n_failed=`expr $n_failed + 1`
	else
	   echo "There was something wrong with the diff command"
	fi
done

echo

if [ $n_failed -eq 0 ] ; then
  	echo "all tests passed"
else
	echo  "$n_failed tests failed"
fi
