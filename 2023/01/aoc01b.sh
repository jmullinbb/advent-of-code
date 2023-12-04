# replace english with englishdigitenglish, so that concatenated values like "zoneight234" render as
# "zone1oneight234" after the "one" conversion, allowing the "eight" conversion to succeed.
# it's ugly as sin, but it gets the correct value.
 sed -e 's/one/&1&/g' -e 's/two/&2&/g' -e 's/three/&3&/g' -e 's/four/&4&/g' -e 's/five/&5&/g' -e 's/six/&6&/g' -e 's/seven/&7&/g' -e 's/eight/&8&/g' -e 's/nine/&9&/g'
