#!/bin/bash

echo "`date`;"
echo "`whoami`;"
echo "`hostname`;"

echo
echo "Процессор:"

model=$(cat /proc/cpuinfo | grep -m1 'model name' | awk '{print $4, $5, $6, $7, $8, $9}')
echo "Модель – $model"

arch=$(lscpu | grep "Architecture" | awk '{print $2}')
echo "Архитектура – $arch"

hz=$(cat /proc/cpuinfo | grep -m1 'cpu MHz' | awk '{print $4}')
echo "Тактовая частота – $hz"

cores=$(cat /proc/cpuinfo | grep -m1 'cpu cores' | awk '{print $4}')
echo "Количество ядер – $cores"

threads=$(lscpu | grep 'Thread' | awk '{print $4}')
echo "Количество потоков на одно ядро – $threads"

echo
echo "Оперативная память:"

total_ram=$(free -h | grep 'Mem' | awk '{print $2}')
echo "Всего – $total_ram"

free_ram=$(free -h | grep 'Mem' | awk '{print $7}')
echo "Доступно – $free_ram"

echo
echo "Жёсткий диск:"

#sda1 заменяем при необходимости

total_hdd=$(df -H | grep '/dev/sda1' | awk '{print $2}')
echo "Всего – $total_hdd"

free_hdd=$(df -H | grep '/dev/sda1' | awk '{print $4}')
echo "Всего – $free_hdd"

mounted_on=$(df -H | grep '/dev/sda1' | awk '{print $6}')
echo "Смонтировано в корневую директорию – $mounted_on"

total_swap=$(free -h | grep 'Swap' | awk '{print $2}')
echo "Swap всего – $total_swap"

free_swap=$(free -h | grep 'Swap' | awk '{print $4}')
echo "Swap всего – $free_swap"

echo
echo "Сетевые интерфейсы:"

num_of_ports=0;
for iface in $(ls /sys/class/net/)
do 
num_ports=$[$num_ports+1]
done

echo
echo "Количество сетевых интерфейсов – $num_ports"
echo

echo -e "Имя cетевого интерфейса \t MAC адрес \t\t IP адрес \t Скорость соединения"

for iface in $(ls /sys/class/net/)
do 
echo -e "$iface\t\t\t \c"

mac="$(ifconfig $iface | grep -i "ether" | awk '{print $2}')"
if [[ -n $mac ]];
then
	echo -e "\t $mac \t \c"
else
	echo -e "\t null \t\t\t \c"
fi

ip="$(ifconfig $iface | grep -i "inet " | awk '{print $2}')"
if [[ -n $ip ]];
then
	echo -e "$ip \t \c"
else
	echo -e "null \t\t \c"
fi

speed=$(cat /sys/class/net/$iface/speed 2> /dev/null)

if [[ $speed ]]
then
	echo $speed
else
	echo "null"
fi
done