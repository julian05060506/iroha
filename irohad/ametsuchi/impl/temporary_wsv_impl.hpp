/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_TEMPORARY_WSV_IMPL_HPP
#define IROHA_TEMPORARY_WSV_IMPL_HPP

#include <pqxx/connection>
#include <pqxx/nontransaction>
#include "ametsuchi/temporary_wsv.hpp"

namespace iroha {
  namespace ametsuchi {
    class TemporaryWsvImpl : public TemporaryWsv {
     public:
      TemporaryWsvImpl(std::unique_ptr<pqxx::lazyconnection> connection,
                       std::unique_ptr<pqxx::nontransaction> transaction,
                       std::unique_ptr<WsvQuery> wsv,
                       std::unique_ptr<WsvCommand> executor);
      bool apply(const model::Transaction &transaction,
                 std::function<bool(const model::Transaction &, WsvCommand &,
                                    WsvQuery &)>
                     function) override;
      nonstd::optional<model::Account> getAccount(
          const std::string &account_id) override;
      nonstd::optional<std::vector<ed25519::pubkey_t>> getSignatories(
          const std::string &account_id) override;
      nonstd::optional<model::Asset> getAsset(
          const std::string &asset_id) override;
      nonstd::optional<model::AccountAsset> getAccountAsset(
          const std::string &account_id, const std::string &asset_id) override;
      nonstd::optional<std::vector<model::Peer>> getPeers() override;
      ~TemporaryWsvImpl() override;

     private:
      std::unique_ptr<pqxx::lazyconnection> connection_;
      std::unique_ptr<pqxx::nontransaction> transaction_;
      std::unique_ptr<WsvQuery> wsv_;
      std::unique_ptr<WsvCommand> executor_;
    };
  }  // namespace ametsuchi
}  // namespace iroha

#endif  // IROHA_TEMPORARY_WSV_IMPL_HPP
