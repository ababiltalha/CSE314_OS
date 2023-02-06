g++ cigarette_zem.c zemaphore.c -o cigarette_zem -lpthread
echo " ### Running cigarette_zem.c"
./cigarette_zem
echo "-----------------------------"
echo " ### Running cigarette_cv.c"
g++ cigarrete_cv.c -o cigarrete_cv -lpthread
./cigarrete_cv