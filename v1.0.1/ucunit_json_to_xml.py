'''
 uCUnit - A unit testing framework for microcontrollers

 (C) 2018 Balazs Grill - IncQuery Labs Ltd.
     2019 Rainer Poisel - logi.cals GmbH

 File        : ucunit_json_toxml.py
 Description : Python script to convert UCunit JSON output to JUnit-compatible XML reports
 Author      : Balazs Grill
 Contact     : www.ucunit.org

  This file is part of ucUnit.

  You can redistribute and/or modify it under the terms of the
  Common Public License as published by IBM Corporation; either
  version 1.0 of the License, or (at your option) any later version.

  uCUnit is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  Common Public License for more details.

  You should have received a copy of the Common Public License
  along with uCUnit.

  It may also be available at the following URL:
        http://www.opensource.org/licenses/cpl1.0.txt

  If you cannot obtain a copy of the License, please contact the
  author.
'''
import sys
import json
import subprocess
from pathlib import Path
from xml.dom import getDOMImplementation


def check_to_str(check):
    return check["file"] + ":" + check["line"] + " " + check["msg"] + \
        "(" + check["args"] + ") " + check["result"] + "\n"


def set_property(doc, props, name, value):
    prop = doc.createElement("property")
    prop.setAttribute("name", name)
    prop.setAttribute("value", value)
    props.appendChild(prop)


def pretty_print_json_if_possible(input_str):
    try:
        j = json.loads(input_str)
    except json.decoder.JSONDecodeError:
        print(input_str)
        return
    print(json.dumps(j, indent=2))


def main():
    try:
        process_output = subprocess.check_output(sys.argv[2:])
        ret_val = 0
    except OSError:
        print("OSError. Process output:")
        pretty_print_json_if_possible(process_output)
        sys.exit(1)
    except subprocess.CalledProcessError as exc:
        process_output = exc.output
        ret_val = exc.returncode
        print("CalledProcessError. Process output:")
        pretty_print_json_if_possible(process_output)
        print("Return code: " + str(ret_val))

    inp = process_output.decode('ascii')
    try:
        data = json.loads(inp)
    except json.decoder.JSONDecodeError as err:
        print("Process output:")
        print(process_output)
        print("Decoded output:")
        print(inp)
        print("End")
        raise err
    impl = getDOMImplementation()

    doc = impl.createDocument(None, "testsuite", None)
    root = doc.documentElement

    totaltests = int(data["passed"]) + int(data["failed"])
    root.setAttribute("name", data["name"])
    root.setAttribute("tests", str(totaltests))
    root.setAttribute("errors", "0")
    root.setAttribute("failures", data["failed"])
    props = doc.createElement("properties")
    set_property(doc, props, "compiled", data["compiled"])
    set_property(doc, props, "time", data["time"])
    set_property(doc, props, "ucunit-version", data["version"])
    root.appendChild(props)

    for testcase in data['testcases']:
        if 'testcasename' in testcase:
            tcelement = doc.createElement('testcase')
            tcelement.setAttribute("name", testcase['testcasename'])
            failures = ""
            stdout = ""
            for check in testcase["checks"]:
                if "result" in check:
                    if check["result"] == "passed":
                        stdout += check_to_str(check)
                    else:
                        failures += check_to_str(check)
            root.appendChild(tcelement)
            sysout = doc.createElement('system-out')
            sysout.appendChild(doc.createCDATASection(stdout))
            tcelement.appendChild(sysout)
            if testcase["result"] != "passed":
                failure_elem = doc.createElement("failure")
                failure_elem.appendChild(doc.createTextNode(failures))
                tcelement.appendChild(failure_elem)
        else:
            if testcase:
                raise Exception('Invalid test case')

    p = Path(sys.argv[1])
    if str(p.parents[1]) != ".":
        p.parents[0].mkdir(parents=True, exist_ok=True)

    with open(sys.argv[1], mode='w') as fh:
        fh.write(doc.toxml('utf-8').decode('utf-8'))

    sys.exit(ret_val)


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: " + sys.argv[0] + " <output-file> <executable> [args]")
        sys.exit(1)
    main()
