# read stdin,
# strip alphabetic chars
# repeat single char to make next step easier
# replace strings of chars with first and last chars (they're all digits now)
# read column of numbers with jq and apply the "add" filter
cat | tr -d 'a-z' | sed -re 's/^.$/&&/' -e 's/^(.).*(.)$/\1\2/' | jq -s add
