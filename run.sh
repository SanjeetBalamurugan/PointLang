# Create Build Files
edit="gmake"

./vendor/premake/premake5 $edit
make
if [[ $? == 0 ]]; then
  printf "PointLang StartsHere\n\n"
  ./bin/Debug/PointLang
fi
