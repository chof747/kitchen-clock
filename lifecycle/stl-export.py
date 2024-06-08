import FreeCAD
import Part
import Mesh
import os
import sys

# Define the directories
components_dir = '3dmodel/components'
stl_dir = '3dmodel/stl'

# Ensure the STL directory exists
if not os.path.exists(stl_dir):
  os.makedirs(stl_dir)

# Scan for FCStd files in the components directory
for filename in os.listdir(components_dir):
  if filename.endswith('.FCStd'):
    # Load the FreeCAD document
    doc_path = os.path.join(components_dir, filename)
    base_name = os.path.splitext(filename)[0]

    print("\n#####")
    print(f'Opening: {base_name} from "{doc_path}"')

    doc = None        
    try:
      # Load the FreeCAD document
      doc = FreeCAD.open(doc_path)
    except Exception as e:
      print(f"Exception opening file: {doc_path} [{e}]")
      continue
    
    # Export each body as an STL file
    for obj in doc.Objects:
      if obj.TypeId == 'PartDesign::Body' and obj.Shape.Volume != 0 and obj.Label == base_name:
        stl_path = os.path.join(stl_dir, f"{base_name}.stl")
        Mesh.export([obj], stl_path)
        print(f"Exported {stl_path}")
          

    # Close the document
    FreeCAD.closeDocument(doc.Name)

print("Exporting complete.")
sys.exit(0)
