control_c() {
   kill -9 `pidof ./client_exec`
   kill -9 `pidof ./BusIoTSystem`
   exit
}
i=0;
while true ; do
    trap control_c SIGINT
    if i==0;then
    ./client_exec
    let i+1
    fi
done
