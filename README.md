# chbs
A lightweight, POSIX compliant program to generate secure and memorable passwords from your terminal. Features a wordlist of 4096 words (12 bits of entropy per word) derived from the [Oxford 5000](https://www.oxfordlearnersdictionaries.com/us/wordlists/oxford3000-5000).

Inspired by [https://xkcd.com/936/](https://xkcd.com/936).

![suck it randall i can alt text too](https://imgs.xkcd.com/comics/password_strength.png)

```
Usage: chbs [-c|-C] [-n] [-w WORDCOUNT]
   or: chbs [-c|-C] -s SEPARATOR [-w WORDCOUNT]

  -c        capitalizes first letter of each word
  -C        capitalizes all letters of each word
  -n        does not print a separator between each character
  -s        uses SEPARATOR as custom separator (valid separators: ASCII 32-126)
  -w        prints WORDCOUNT words
```

Defaults to 7 words (84 bits of entropy).
