# Create Build Files
edit="gmake"

./gen.sh $edit
make
if [[ $? == 0 ]]; then
  printf "PointLang StartsHere\n\n"
  ./bin/Debug/PointLang
fi
