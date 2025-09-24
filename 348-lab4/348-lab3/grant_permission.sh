#!/bin/bash
chmod 751 ~
chmod 755 ~/public_html
find ~/public_html -type d -exec chmod 755 {} \;
find ~/public_html -type f -exec chmod 644 {} \;

