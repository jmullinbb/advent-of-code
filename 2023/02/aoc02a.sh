cat | sed -re 's/ ((([1-9]|1[0-3]) green)|(([1-9]|1[0-2]) red)|(([1-9]|1[0-4]) blue))/ /g' -e '/red|green|blue/d' -e 's/Game *([0-9]+):.*$/\1/' | jq -s add
