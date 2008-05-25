(function() {
    // Find callouts in the document and setup their event handlers
    window.onload = function() {
        // Find: '.callout_bug a, .line_callout_bug a'
        var anchors = document.getElementsByTagName('a');
        var found = false;
        for(var i = 0, anchor; anchor = anchors[i]; ++i) {
            for(var callout = anchor.parentNode;
                callout && (callout.className != 'callout_bug' &&
                    callout.className != 'line_callout_bug');
                callout = callout.parentNode) {}
            var url = parse_url(anchor.href);
            if(callout && url && url.fragment) {
                found = true;
                callout.onmouseover = callout_mouseover;
                callout.onmouseout = callout_mouseout;
                callout.target_fragment = url.fragment;
            }
        }

        if(found) {
            document.body.onmousemove = mousemove;
            window.onunload = cleanup;
        }
    };

    // Currently displayed popup node, if there is one.
    var popup;
    
    // Function which checks if the current mouse position is within the
    // bounding shape containing the current popup and its callout.
    var bounds;
    
    // The callout that the cursor is currently over (not necessarily the
    // callout for the current popup).
    var callout;

    // Display the popup for the given callout.
    function callout_popup(element) {
        var target = get_callout_target(element);
        var offset = get_offset(element);

        var new_popup = document.createElement('div');  
        new_popup.style.background = "#fff";
        new_popup.style.color = "#000";
        new_popup.style.border = "1px solid black";
        new_popup.style.visibility = "hidden";
        new_popup.style.position = "absolute";
        new_popup.style.top = offset.top + "px";
        new_popup.style.left = offset.left + "px";

        var popup_child = document.createElement('div');
        popup_child.style.margin = "1em";

        for(var i = 0; i < target.childNodes.length; ++i)
            popup_child.appendChild(target.childNodes[i].cloneNode(true));

        new_popup.appendChild(popup_child);

        document.body.appendChild(new_popup);
        new_popup.style.top = (offset.top - new_popup.offsetHeight) + "px";
        new_popup.style.visibility = "visible";

        popup = new_popup;
        bounds = bounding_poly(offset, {
            top: (offset.top - new_popup.offsetHeight),
            bottom: offset.top,
            left: offset.left,
            right: offset.left + new_popup.offsetWidth
        });
    }

    // Close the current popup, if there is one.
    function clear_popup() {
        if(popup) {
            popup.parentNode.removeChild(popup);
            popup = null;
            bounds = null;
        }
    }

    // Clear all variables, called when leaving the page. Hopefully this will
    // help prevent memory leaks.
    function cleanup() {
        clear_popup();
        if(callout) callout = null;
        bounds = null;
    }

    // If there isn't a current callout popup, display one for this callout.
    // Maybe I should introduce a timeout if there is a current popup?
    function callout_mouseover() {
        callout = this;
        if(!popup) callout_popup(this);
    }

    function callout_mouseout(event) {
        callout = null;
    }

    // If the mouse movement causes the cursor to leaving the bounding area
    // for the current popup, hide it.
    function mousemove(event) {
        if(popup) {
            event = event || window.event;
            var x = 0, y = 0;

            if(event.pageX || event.pageY) {
                x = event.pageX;
                y = event.pageY;
            }
            else if(event.clientX || event.clientY) {
                x = event.clientX + document.body.scrollLeft;
                y = event.clientY + document.body.scrollTop;
            }

            if(!bounds(x, y)) {
                clear_popup();

                // If the cursor is over another callout then display it.
                // Maybe I should check that this isn't the same callout,
                // just in case.
                if(callout) callout_popup(callout, event)
            }
        }
    }

    // Returns a function which checks if a given point is inside the convex
    // hull of the two boxes.
    function bounding_poly(box1, box2) {
        var left = Math.min(box1.left, box2.left),
            right = Math.max(box1.right, box2.right),
            top = Math.min(box1.top, box2.top),
            bottom = Math.max(box1.bottom, box2.bottom)

        var lines = [];

        if(box2.left < box1.left ||
                (box2.left == box1.left && box2.top < box1.top)) {
            swap_boxes();
        }

        if(box2.top < box1.top) {
            add_line(box1.left, box1.top, box2.left, box2.top);
            swap_boxes();
        }

        if(box2.right > box1.right) {
            add_line(box1.right, box1.top, box2.right, box2.top);
            swap_boxes();
        }

        if(box2.bottom > box1.bottom) {
            add_line(box1.right, box1.bottom, box2.right, box2.bottom);
            swap_boxes();
        }

        if(box2.left < box1.left) {
            add_line(box1.left, box1.bottom, box2.left, box2.bottom);
            swap_boxes();
        }

        return function(x, y) {
            if(x < left || x >= right || y < top || y >= bottom)
                return false;
            for(var i = 0, line; line = lines[i]; ++i) {
                if((x-line.x) * line.ydiff - (y-line.y) * line.xdiff > 0) {
                    return false;
                }
            }
            return true;
        }

        function swap_boxes() {
            var tmp = box1; box1 = box2; box2 = tmp;
        }

        function add_line(x1, y1, x2, y2) {
            lines[lines.length] =
                {x: x1, y: y1, xdiff: x2-x1, ydiff: y2-y1};
            swap_boxes();
        }
    }

    // Break a url into its constituent parts.
    // Doesn't decode any encoded characters.
    // Regular expression from: http://tools.ietf.org/html/rfc3986#appendix-B
    function parse_url(url) {
        var m =
            /^(([^:\/?#]+):)?(\/\/([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?$/
            .exec(url);
        if(m)
            return {
                protocol: m[2],
                host: m[4],
                path: m[5],
                query: m[7],
                fragment: m[9]
            };
    }

    // Find the destination text for a callout
    function get_callout_target(callout) {
        for(var target = get_fragment(callout.target_fragment);
            target && target.nodeName.toLowerCase() != 'td';
            target = target.parentNode) {}
        if(!target) return;
        for(target = target.nextSibling;
            target && target.nodeName.toLowerCase() != 'td';
            target = target.nextSibling) {}
        return target;
    }
    
    // Find the target of a fragment identifier.
    function get_fragment(fragment) {
        var element = document.getElementById(fragment);
        if(element) return element;
        for(var i = 0; i < document.anchors.length; ++i) {
            if(document.anchors[i].name == fragment)
                return document.anchors[i];
        }
    }

    // Find the position and dimensions of an element. I should probably use
    // a javascript library as this doesn't deal with the many special cases
    // that can come up.
    function get_offset(element) {
        if(element.getBoundingClientRect) {
            var box = element.getBoundingClientRect();
            var addleft =
                    Math.max(document.documentElement.scrollLeft,
                        document.body.scrollLeft) -
                        (document.documentElement.clientLeft || 0),
                addtop =
                    Math.max(document.documentElement.scrollTop,
                        document.body.scrollTop) -
                        (document.documentElement.clientTop || 0);
            return {
                left: Math.floor(box.left) + addleft,
                right: Math.ceil(box.right) + addleft,
                top: Math.floor(box.top) + addtop,
                bottom: Math.ceil(box.bottom + addtop)
            };
        } else {
            var left = element.offsetLeft, top = element.offsetTop;
            for(var parent = element.offsetParent; parent;
                parent = parent.offsetParent) {
                left += parent.offsetLeft;
                top += parent.offsetTop;
            }
            return { left: left, right: left + element.offsetWidth,
                top: top, bottom: top + element.offsetHeight };
        }
    }
})();
