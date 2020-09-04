
<br />
<p align="center">
    <img src="https://user-images.githubusercontent.com/60937471/92208053-9ed21400-ee9f-11ea-8084-5f6b54372ea6.jpg" alt="Logo" width="120" height="120">
  

  <h3 align="center">Jahan Bank</h3>

  <p align="center">
an awsome banking system with ATM, Dynamic password ...    <br />
<br />
<br />

  </p>
</p>

##### Note:admin's user name: Jahan admin's password: JahanBank



## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
  * [Bank](#bank)
    * [Accounts](#Accounts)
    * [Users](#Users)
    * [Admin](#Admin)
    * [Account Services](#Account-Services)
  * [ATM](#ATM)
  * [Dynamic Password](#Dynamic-Password)
    * [Server](#Server)
    * [Socket](#Socket)
* [License](#license)
* [Contact](#contact)



## About The Project
![screen1](https://user-images.githubusercontent.com/60937471/92209672-a47d2900-eea2-11ea-8de1-9a691f422065.PNG)

In this project a banking system is implemented. In this system, you have two types of normal users and administrators.
Users can open an account and perform related operations. The manager is also able to manage users and processes. Also
The payment gateway is designed so that money can be transferred with the help of a bank card.
 

### Built With

* C++
* QT Libs

### Bank

#### Accounts
the user can create four types of bank accounts, which are:  
* **lend** : This account is used for savings and can be deposited or withdrawn at any time. The account holder can apply for a bank card.

* **short-term** : This account is the same as the lend account, with the difference that at the end of each month, it receives a 5% interest. The owner of this account can also
Apply for a bank card.
* **company** : This account is the same as the short-term account, with the difference that account opener can introduce up to 3 other peaople as account holders.
* **long-term** : This account is used for investment. at the end of each 3 month, it receives a 15% interest. If you do not withdraw for another three months, it will receive another 15% interest. From the moment you make your first withdrawal, your account becomes a short-term account and
You will be paid interest according to the rules of that account. The owner of this type of bank account can not apply for a card . pay attention When this account becomes short-term, you can apply for a card.



 For each of these accounts, account number, account creation date and account balance is maintained.


#### Users
 normal users can:
 * **Request to open a new account** : request for will be sent and the admin can approve or reject the request.
 * **View accounts** : accounts approved by admin can be viewed.
 * **Edit profile** : user's profile includes national code, first and last name, date of birth, username and password.(password must be strong) 
 * **View login and logout times**

#### Admin
System has an administrator and other users will be added. admin can:

* **Manage users** :
  * See the list of users with details.
  * See the login and logout history of each user.
  * Add a user to the system by entering the profile details.
  * Remove a user.
 
* **Manage account requests** : Approve or reject all unverified account requests. After veryfying the account, an account number will be assigned to.
* **Manage card requests** : Approve or reject all unverified card requests. After veryfying the card, a card number will be assigned to. Also a four-digit CVV2
Is determined. The expiration date of the card is one year after approving.
* **View Transactions** : See all the transactions performed along with their details such as the origin and destination and the amount of the transaction.
* **Manage accounts and cards** :
  * See the list of accounts and cards of each user with details.
  * Block or unblock an account or card

#### Account Services
After confirming the account request, user can:
 * **Receive balance**
 * **Money transfer**
 * **View the last ten transactions**
 * **View the last ten transactions in `PDF format`.**
 * **Send E-mail after each transaction**
 * **card request:**
 * **Request a dynamic password** 
 *This password is valid for two minutes*


### Dynamic Password
![screen2](https://user-images.githubusercontent.com/60937471/92209676-a5ae5600-eea2-11ea-9226-e8030e1d733c.PNG)

#### Server
using "QTCPServer" while the application is running a server is running too. it produces dynamic password when client requests.
#### Socket
another application is designed for client. using QTCPSocket user can request for dynamic password by (username-password-card number).

##### Note:The application only works when Server is connected, so Bank must be running
### ATM
![screen3](https://user-images.githubusercontent.com/60937471/92247198-20479780-eedc-11ea-8f05-9de7494e3884.PNG)
<br>
In this portal, the card number of origin and destination and amount of money as well as The specifications of the source card including CVV2 and dynamic password and the expiration date of the card are received card.
then the money transfers.
## License

Distributed under the MIT License.



## Contact



Leila Alavi: lsat1379@gmail.com
<br>
Bank: jahanbankingsystem@gmail.com

Project Link: [https://github.com/lsatc/banking-system](https://github.com/lsatc/banking-system)


##### Note:it only works when Server is connected, so Bank must be running
