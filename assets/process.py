#!/usr/bin/env python
"""Process script copy & paste template."""

import json
import collections
import re

with open('instructions.json') as fi:
    fi = fi.read()

data = json.loads(fi, object_pairs_hook=collections.OrderedDict)
defs = data['definitions']

# ... processing code here ...

with open('instructions.json', 'w') as of:
    json.dump(data, of)
