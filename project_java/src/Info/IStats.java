package Info;

public interface IStats {
    void statsGeral(CatUsers u, CatBusiness b, CatReviews r);
    String getFicheiroU();
    String getFicheiroB();
    String getFicheiroR();
    int getWrongReviews();
    int getReviewsSemImpacto();
    int getTotalBusinesses();
    int getTotalBusinessesAvaliados();
    int getTotalUsers();
    int getTotalUsersAtivos();
}
