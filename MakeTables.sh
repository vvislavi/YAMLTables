rm OutputFiles/*
cp YAMLHeader OutputFiles/submission.yaml
echo "Producing tables for HEP"
root -l MakeTables.C
echo "Producing a tarball"
tar -zcvf DataForHEP.tar.gz OutputFiles > dummy
rm dummy
echo "All done!"
