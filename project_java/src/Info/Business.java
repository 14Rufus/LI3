package Info;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.lang.String;

public class Business implements Serializable, Compare,IBusiness {
    private String id;
    private String name;
    private String city;
    private String state;
    private List<String> categories;
    private int ncategories;

    public Business(){
        this.id = null;
        this.name = null;
        this.city = null;
        this.state = null;
        this.categories = null;
        this.ncategories = 0;

    }

    public Business(String id, String name, String city, String state, List<String> categories, int ncategories) {
        this.id = id;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = categories;
        this.ncategories = ncategories;
    }

    public Business(Business b){
        this.id = b.id;;
        this.name = b.name;
        this.city = b.city;
        this.state = b.state;
        this.categories = b.getBusinessCategories();
        this.ncategories = b.ncategories;

    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getCity() {
        return city;
    }

    public String getBusinessState() {
        return state;
    }

    public List<String> getBusinessCategories() {
        return new ArrayList<>(this.categories);
    }

    public int getBusinessNcategories() {
        return ncategories;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public void setState(String state) {
        this.state = state;
    }

    public void setCategories(List<String> categories) {
        this.categories = categories;
    }

    public void setNcategories(int ncategories) {
        this.ncategories = ncategories;
    }

    public Business clone(){
        return new Business(this);
    }

    public String toString() {
        return  "Business -> Id:" + id + '\n' +
                "Nome: " + name + '\n' +
                "Cidade: " + city + '\n' +
                "Estado: " + state + '\n' +
                "Número de categorias:" + ncategories + "\n" +
                "Lista de categorias:" + categories + "\n" ;
    }

    @Override
    public int compareTo(Object b) {
        Business b1 = (Business) b;
        if (this.getId().equals(b1.getId()))
            return 0;
        else
            return 1;
        }
}

