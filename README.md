I was looking for a quick tool to grab the first instance of useful data in a large number of files and couldn't find any.

For example, I wanted to do something like for %i in ( *.html ) do grabtool "\<H1\>" "\</H1\>" %i >> titles.txt

Note that you can also do something like gtool "id=\\"content\\">"

So this is a trivial tool - it understands wchar files.
