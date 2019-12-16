make clean
make build
rm /home/luigi/Documente/pa/proiect/resurse/MyBot
rm /home/luigi/Documente/pa/proiect/resurse/replays/*
cp ./MyBot /home/luigi/Documente/pa/proiect/resurse/MyBot
cd /home/luigi/Documente/pa/proiect/resurse
python ./run.py --cmd "./MyBot" --round 3
rm *.log
cd ../l2*