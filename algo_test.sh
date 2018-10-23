for entry in "./testingGrids"/*
do
  echo " - - - - - - - - - - -"
  echo "Testing file $entry"
  echo "Algorithm n1"
  ./bin -f "$entry" 1 0
  echo "Algorithm n2"
  ./bin -f "$entry" 2 0
  echo "Algorithm n3"
  ./bin -f "$entry" 3 0
  echo "Algorithm n4"
  ./bin -f "$entry" 4 0
  echo "\n\n"
done
