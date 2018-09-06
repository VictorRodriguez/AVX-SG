CPUs=$(($(grep -c ^processor /proc/cpuinfo)-1))
for file in build/stress_add_avx2
do
    echo
    echo Running $file in $CPUs CPUs
    for cpu in $(seq 0 $CPUs)
    do 
        ./$file &
        PID=$!
        echo PID = $PID , CPU = $cpu
        taskset -cp $cpu $!
    done
    wait $PID
done

