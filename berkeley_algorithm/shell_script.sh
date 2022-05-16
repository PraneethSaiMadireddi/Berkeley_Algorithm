leader=$1;
numProcess=$2;

for((i=1;i<$numProcess+1;i++))
do      
        if(($i != $leader))
        then
           
	   cmdd="./bt.out $i $leader $numProcess &"
	   eval $cmdd
	fi 
done
sleep 0.5
cmdd="./bt.out $leader $leader $numProcess"

eval $cmdd
wait

