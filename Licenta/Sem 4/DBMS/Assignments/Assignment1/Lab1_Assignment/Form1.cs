using System;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;


namespace Lab1_Assignment
{
    public partial class Form1 : Form
    {
        private string connectionString = "Data Source=DESKTOP-NN3D6V8\\SQLEXPRESS;Initial Catalog=RapDB;Integrated Security=True";
        private SqlDataAdapter daParent, daChild;
        private BindingSource bsParent, bsChild;
        private DataSet dataSet;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string sqlConn = connectionString;
            dataSet = new DataSet();

            daParent = new SqlDataAdapter(getParentQuery(), sqlConn);
            SqlCommandBuilder cb = new SqlCommandBuilder(daParent);
            daParent.Fill(dataSet, getParentTable());

            daChild = new SqlDataAdapter(getChildQuery(), sqlConn);
            cb = new SqlCommandBuilder(daChild);
            daChild.Fill(dataSet, getChildTable());

            DataRelation drel = new DataRelation("fk_child_parent",
                dataSet.Tables[getParentTable()].Columns[getPKName()],
                dataSet.Tables[getChildTable()].Columns[getFKName()]);
            dataSet.Relations.Add(drel);

            bsParent = new BindingSource();
            bsParent.DataSource = dataSet;
            bsParent.DataMember = getParentTable();

            bsChild = new BindingSource();
            bsChild.DataSource = bsParent;
            bsChild.DataMember = "fk_child_parent";

            dataGridView1.DataSource = bsParent;
            dataGridView2.DataSource = bsChild;
        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {
            int parentID = (int)dataGridView1.CurrentRow.Cells[getPKName()].Value;

            BindingSource childBindingSource = (BindingSource)dataGridView2.DataSource;
            if (childBindingSource != null)
            {
                childBindingSource.Filter = $"{getFKName()} = {parentID}";
            }
        }

        private void button1_Click(object sender, EventArgs e) // Add button
        {
            
        }

        private void button2_Click(object sender, EventArgs e) // Update button
        {
            this.daParent.Update(this.dataSet, getParentTable());
            this.daChild.Update(this.dataSet, getChildTable());
        }

        private void button3_Click(object sender, EventArgs e) // Delete Button
        {
            if (dataGridView2.SelectedRows.Count > 0)
            {
                DataGridViewRow selectedRow = dataGridView2.SelectedRows[0];
                DataRowView selectedRowView = (DataRowView)selectedRow.DataBoundItem;

                int primaryKeyValue = Convert.ToInt32(selectedRowView.Row[getPKNameChild()]);

                dataGridView2.Refresh();

                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();

                    SqlCommand command = new SqlCommand();
                    command.Connection = connection;
                    command.CommandText = "DELETE FROM " + getChildTable() + " WHERE " + getPKNameChild() + " = @PrimaryKey";
                    command.Parameters.AddWithValue("@PrimaryKey", primaryKeyValue);

                    command.ExecuteNonQuery();
                }

                selectedRowView.Delete();
            }
        }

        private string getPKName()
        {
            return ConfigurationManager.AppSettings["parent_table_pk"];
        }

        private string getFKName()
        {
            return ConfigurationManager.AppSettings["child_table_fk"];
        }

        private string getPKNameChild()
        {
            return ConfigurationManager.AppSettings["child_table_pk"];
        }

        private string getParentTable()
        {
            return ConfigurationManager.AppSettings["parent_table"];
        }

        private string getParentQuery()
        {
            return ConfigurationManager.AppSettings["parent_query"];
        }

        private string getChildTable()
        {
            return ConfigurationManager.AppSettings["child_table"];
        }
        private string getChildQuery()
        {
            return ConfigurationManager.AppSettings["child_query"];
        }

        private string getConnectionString()
        {
            return ConfigurationManager.ConnectionStrings["connection_string"].ConnectionString.ToString();
        }
    }
}
