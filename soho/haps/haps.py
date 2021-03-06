import collections, types
import logging, sys, os
from collections import defaultdict

if os.getenv("HAPS_USE_ELEMENTTREE", None):
    from xml.etree.ElementTree import Element, tostring
else:
    from etree_impl import Element, tostring


logging.basicConfig(stream=sys.stderr, level=logging.DEBUG)
logger = logging.getLogger(__name__)

FORMAT_REVISION = 27

class HapsVal(Element):
    def __init__(self, values):
        super(HapsVal, self).__init__()
        self.set('text', values)


class HapsObj(Element):
    """Element object which maps to all XML elements except elmenents
    consisting with only text (numeric). It uses etree compilant implementation
    as its base class (albeit at this point xml.etree.ElementTree might not work.)
    """
    def __init__(self, name=None, **kwargs):
        """Init object with attribs from kwargs."""
        super(HapsObj, self).__init__(name, **kwargs)

    def add(self, obj):
        """ Alias for append or extend.
        """
        #FIXME might want to remove it.
        if isinstance(obj, list) or isinstance(obj, tuple)\
            and type(obj) != HapsVal:
            return self.extend(obj)
        else:
            return self.append(obj)

    def __repr__(self):
        return tostring(self)

    def tostring(self, pretty_print=True):
        return tostring(self, pretty_print)

    def add_parms(self, parms):
        """Constructs & appends a parameters objects 
           from provided list of tuples suitable for parm's initalization.

           :parm parms: List of tuples [(str name, str value), (...,...)]
           :returns:    self
        """
        from tags import Parameter
        assert isinstance(parms, collections.Iterable)
        [self.append(Parameter(parm[0], parm[1])) for parm in parms\
             if len(parm) == 2 and isinstance(parm[0], str)]
        return self

    def get_by_type(self, typename):
        return self.findall(typename)

    def get_by_name(self, name, typename=None):
        """ Search for an item named 'name'.
            Optional 'typename' scopes the search. 
        """
        if typename:
            children = self.findall(typename)
            for child in children:
                if child.get('name', False) == name:
                    return child
        else: 
            for child in list(self):               
                if child.get('name', False) == name:
                    return child

        return None
 




 


















