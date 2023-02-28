
fn main() {
    let obj_file: String = std::env::args()
        .skip(1)
        .next()
        .expect("A .obj file to print is required");

    let (models, materials) =
        tobj::load_obj(
            &obj_file,
            &tobj::LoadOptions::default()
        )
        .expect("Failed to OBJ load file");  
}
