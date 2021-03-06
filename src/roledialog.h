#ifndef ROLEDIALOG_H
#define ROLEDIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include "global_enums.h"

class DFInstance;
class Dwarf;
class Material;
class Plant;
class Preference;
class QSplitter;
class QTableWidget;
class QTreeWidgetItem;
class Role;
class RoleAspect;
namespace Ui { class roleDialog; }

class roleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit roleDialog(DFInstance *dfi, QWidget *parent = 0);
    ~roleDialog();
    bool event(QEvent *evt);

    void load_role(QString role_name);

public slots:
    void selection_changed();

private:
    Ui::roleDialog *ui;
    Role *m_role;
    QColor color_override;
    QColor color_default;
    DFInstance *m_df;
    Dwarf *m_dwarf;

    //preference main holder
    QHash<QTreeWidgetItem*,QVector<Preference*>* > m_pref_list;

    //specific categories
    QTreeWidgetItem *m_gems;
    QTreeWidgetItem *m_glass;
    QTreeWidgetItem *m_metals;
    QTreeWidgetItem *m_stone;
    QTreeWidgetItem *m_wood;
    QTreeWidgetItem *m_glazes_wares;
    QTreeWidgetItem *m_plants;
    QTreeWidgetItem *m_plants_alcohol;
    QTreeWidgetItem *m_plants_crops;
    QTreeWidgetItem *m_plants_crops_plantable;
    QTreeWidgetItem *m_plants_mill;
    QTreeWidgetItem *m_plants_extract;
    QTreeWidgetItem *m_trees;
    QTreeWidgetItem *m_fabrics;

    //creature categories
    QTreeWidgetItem *m_creatures;
    QTreeWidgetItem *m_hateable;
    QTreeWidgetItem *m_trainable;
    QTreeWidgetItem *m_milkable;
    QTreeWidgetItem *m_extracts;
    QTreeWidgetItem *m_extracts_fish;
    QTreeWidgetItem *m_fishable;
    QTreeWidgetItem *m_shearable;
    QTreeWidgetItem *m_butcher;
    QTreeWidgetItem *m_domestic;

    QTreeWidgetItem *m_creature_mats;

    //general categories
    QTreeWidgetItem *m_general_item;
    QTreeWidgetItem *m_general_material;
    QTreeWidgetItem *m_general_creature;
    QTreeWidgetItem *m_general_trade_good;
    QTreeWidgetItem *m_general_plant_tree;
    QTreeWidgetItem *m_general_other;
    QTreeWidgetItem *m_general_equip;

    //preference include/exclude lists
    QVector<ITEM_TYPE> item_ignore;
    QVector<MATERIAL_FLAGS> mats_include;

    void load_role_data();
    void decorate_splitter(QSplitter *s);
    void load_aspects_data(QTableWidget &table, QHash<QString, RoleAspect *> aspects);
    void save_aspects(QTableWidget &table, QHash<QString, RoleAspect*> &list);
    void save_prefs(Role *r);
    void insert_row(QTableWidget &table, RoleAspect *a, QString key);
    void insert_pref_row(Preference *p);

    void add_aspect(QString id, QTableWidget &table, QHash<QString,RoleAspect*> &list);

    void clear_table(QTableWidget &t);
    bool m_override;

    //preferences
    void add_general_node(const QString title, PREF_TYPES ptype, QList<int> &flags, QTreeWidgetItem *parent, ITEM_TYPE itype = NONE);
    void build_pref_tree();
    void load_material_prefs(QVector<Material*> mats, QString prefix_name = "", MATERIAL_STATES state_name = GENERIC);
    void load_plant_prefs(QVector<Plant *> plants);
    void load_items();
    void load_creatures();
    void add_general_creature_node(const QString suffix, QList<int> &flags, QTreeWidgetItem **parent_node);
    void load_weapons();
    QTreeWidgetItem* init_parent_node(QString title);
    void add_pref_to_tree(QTreeWidgetItem *parent, Preference *p);
    bool check_flag(Material *m, Preference *p, MATERIAL_FLAGS flag);

protected:
    void closeEvent(QCloseEvent *){close_pressed();}
    void keyPressEvent(QKeyEvent *e){
        if(e->key()==Qt::Key_Escape)
            close_pressed();
    }

private slots:
    void close_pressed();
    void save_pressed();
    void save_role(Role *);
    void copy_pressed();
    void name_changed(QString text);

    //attributes
    void draw_attribute_context_menu(const QPoint &);
    void add_attribute();
    void remove_attribute();

    //traits
    void draw_trait_context_menu(const QPoint &);
    void add_trait();
    void remove_trait();

    //skills
    void draw_skill_context_menu(const QPoint &);
    void add_skill();
    void remove_skill();

    //void tree_selection_changed(QTreeWidgetItem *current, QTreeWidgetItem *previous);
    void item_double_clicked(QTreeWidgetItem *item, int col);
    void draw_prefs_context_menu(const QPoint &);
    void remove_pref();
    void search_prefs(QString);
    void clear_search();

    //update new role ratings
    void calc_new_role();

signals:
    void role_changed();
};

//Q_DECLARE_METATYPE(Preference*)
#endif // ROLEDIALOG_H
