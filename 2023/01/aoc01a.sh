# read stdin,
# strip alphabetic chars
# repeat single digits to make next step easier
# replace strings of chars with first and last chars (they're all digits now)
# read column of numbers with jq and apply the "add" filter
cat | tr -d '[:alpha:]' | sed -re 's/^(.)$/\1\1/' | sed -re 's/^(.).*(.)$/\1\2/' | jq -s add
